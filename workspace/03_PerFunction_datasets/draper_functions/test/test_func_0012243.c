lp3943_pwm_free_map(struct lp3943_pwm *lp3943_pwm,
				struct lp3943_pwm_map *pwm_map)
{
	struct lp3943 *lp3943 = lp3943_pwm->lp3943;
	int i, offset;

	for (i = 0; i < pwm_map->num_outputs; i++) {
		offset = pwm_map->output[i];
		clear_bit(offset, &lp3943->pin_used);
	}

	kfree(pwm_map);
}
