ath9k_hw_gen_timer_start(struct ath_hw *ah,
			      struct ath_gen_timer *timer,
			      u32 timer_next,
			      u32 timer_period)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;
	u32 mask = 0;

	timer_table->timer_mask |= BIT(timer->index);


	REG_WRITE(ah, gen_tmr_configuration[timer->index].next_addr,
		 timer_next);
	REG_WRITE(ah, gen_tmr_configuration[timer->index].period_addr,
		  timer_period);
	REG_SET_BIT(ah, gen_tmr_configuration[timer->index].mode_addr,
		    gen_tmr_configuration[timer->index].mode_mask);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {


		if ((timer->index < AR_GEN_TIMER_BANK_1_LEN))
			REG_CLR_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				       (1 << timer->index));
		else
			REG_SET_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				       (1 << timer->index));
	}

	if (timer->trigger)
		mask |= SM(AR_GENTMR_BIT(timer->index),
			   AR_IMR_S5_GENTIMER_TRIG);
	if (timer->overflow)
		mask |= SM(AR_GENTMR_BIT(timer->index),
			   AR_IMR_S5_GENTIMER_THRESH);

	REG_SET_BIT(ah, AR_IMR_S5, mask);

	if ((ah->imask & ATH9K_INT_GENTIMER) == 0) {
		ah->imask |= ATH9K_INT_GENTIMER;
		ath9k_hw_set_interrupts(ah);
	}
}
