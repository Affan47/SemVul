ath9k_dump_legacy_btcoex(struct ath_softc *sc, u8 *buf, u32 size)
{

	struct ath_btcoex *btcoex = &sc->btcoex;
	u32 len = 0;

	ATH_DUMP_BTCOEX("Stomp Type", btcoex->bt_stomp_type);
	ATH_DUMP_BTCOEX("BTCoex Period (msec)", btcoex->btcoex_period);
	ATH_DUMP_BTCOEX("Duty Cycle", btcoex->duty_cycle);
	ATH_DUMP_BTCOEX("BT Wait time", btcoex->bt_wait_time);

	return len;
}
