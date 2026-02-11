tuner_get_volume(const struct tuner *tuner)
{
        if (tuner_has_volume_control(tuner)) {
                const struct v4l2_queryctrl *vqc = &tuner->volume_ctrl;
                int volume = get_control(tuner, V4L2_CID_AUDIO_VOLUME);
                return (100.0
                        * (volume - vqc->minimum)
                        / (vqc->maximum - vqc->minimum));
        } else {
                return 100.0;
        }
}
