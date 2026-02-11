lm3533_set_boost_ovp(struct lm3533 *lm3533,
						enum lm3533_boost_ovp ovp)
{
	int ret;

	ret = lm3533_update(lm3533, LM3533_REG_BOOST_PWM,
					ovp << LM3533_BOOST_OVP_SHIFT,
					LM3533_BOOST_OVP_MASK);
	if (ret)
		dev_err(lm3533->dev, "failed to set boost ovp\n");

	return ret;
}
