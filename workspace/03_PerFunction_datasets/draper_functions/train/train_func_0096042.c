ath_led_brightness(struct led_classdev *led_cdev,
			       enum led_brightness brightness)
{
	struct ath_softc *sc = container_of(led_cdev, struct ath_softc, led_cdev);
	u32 val = (brightness == LED_OFF);

	if (sc->sc_ah->config.led_active_high)
		val = !val;

	ath9k_hw_set_gpio(sc->sc_ah, sc->sc_ah->led_pin, val);
}
