max98090_jack_work(struct work_struct *work)
{
	struct max98090_priv *max98090 = container_of(work,
		struct max98090_priv,
		jack_work.work);
	struct snd_soc_codec *codec = max98090->codec;
	int status = 0;
	int reg;


	if (max98090->jack_state == M98090_JACK_STATE_NO_HEADSET) {


		snd_soc_update_bits(codec, M98090_REG_JACK_DETECT,
			M98090_JDWK_MASK, 0);

		msleep(50);

		reg = snd_soc_read(codec, M98090_REG_JACK_STATUS);


		snd_soc_update_bits(codec, M98090_REG_JACK_DETECT,
			M98090_JDWK_MASK, M98090_JDWK_MASK);
	} else {
		reg = snd_soc_read(codec, M98090_REG_JACK_STATUS);
	}

	reg = snd_soc_read(codec, M98090_REG_JACK_STATUS);

	switch (reg & (M98090_LSNS_MASK | M98090_JKSNS_MASK)) {
		case M98090_LSNS_MASK | M98090_JKSNS_MASK:
			dev_dbg(codec->dev, "No Headset Detected\n");

			max98090->jack_state = M98090_JACK_STATE_NO_HEADSET;

			status |= 0;

			break;

		case 0:
			if (max98090->jack_state ==
				M98090_JACK_STATE_HEADSET) {

				dev_dbg(codec->dev,
					"Headset Button Down Detected\n");


				status |= SND_JACK_HEADSET;
				status |= SND_JACK_BTN_0;

				break;
			}


			dev_dbg(codec->dev, "Headphone Detected\n");

			max98090->jack_state = M98090_JACK_STATE_HEADPHONE;

			status |= SND_JACK_HEADPHONE;

			break;

		case M98090_JKSNS_MASK:
			dev_dbg(codec->dev, "Headset Detected\n");

			max98090->jack_state = M98090_JACK_STATE_HEADSET;

			status |= SND_JACK_HEADSET;

			break;

		default:
			dev_dbg(codec->dev, "Unrecognized Jack Status\n");
			break;
	}

	snd_soc_jack_report(max98090->jack, status,
			    SND_JACK_HEADSET | SND_JACK_BTN_0);
}
