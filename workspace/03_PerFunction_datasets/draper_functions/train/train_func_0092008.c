arizona_enable_freerun_sysclk(struct arizona *arizona,
					 struct arizona_sysclk_state *state)
{
	int ret, err;


	ret = regmap_read(arizona->regmap, ARIZONA_FLL1_CONTROL_1, &state->fll);
	if (ret) {
		dev_err(arizona->dev, "Failed to cache FLL settings: %d\n",
			ret);
		return ret;
	}
	ret = regmap_read(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1,
			  &state->sysclk);
	if (ret) {
		dev_err(arizona->dev, "Failed to cache SYSCLK settings: %d\n",
			ret);
		return ret;
	}


	ret = regmap_write(arizona->regmap, ARIZONA_FLL1_CONTROL_1,
			ARIZONA_FLL1_ENA | ARIZONA_FLL1_FREERUN);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to start FLL in freerunning mode: %d\n",
			ret);
		return ret;
	}
	ret = arizona_poll_reg(arizona, 25, ARIZONA_INTERRUPT_RAW_STATUS_5,
			       ARIZONA_FLL1_CLOCK_OK_STS,
			       ARIZONA_FLL1_CLOCK_OK_STS);
	if (ret) {
		ret = -ETIMEDOUT;
		goto err_fll;
	}

	ret = regmap_write(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1, 0x0144);
	if (ret) {
		dev_err(arizona->dev, "Failed to start SYSCLK: %d\n", ret);
		goto err_fll;
	}

	return 0;

err_fll:
	err = regmap_write(arizona->regmap, ARIZONA_FLL1_CONTROL_1, state->fll);
	if (err)
		dev_err(arizona->dev,
			"Failed to re-apply old FLL settings: %d\n", err);

	return ret;
}
