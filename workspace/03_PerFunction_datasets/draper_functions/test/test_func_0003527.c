setRange(double lower, double upper, double singleStep,
                               bool slider)
{
    K_USING_KNUMINPUT_P(priv);

    if (priv->slider) {

        QDoubleSpinBox * spin = d->spin;
        disconnect(spin, SIGNAL(valueChanged(double)),
                   priv->slider, SLOT(setValue(int)));
    }
    d->spin->setRange(lower, upper);
    d->spin->setSingleStep(singleStep);

    setSliderEnabled(slider);

    setReferencePoint(referencePoint());

    layout(true);
    updateLegacyMembers();
}
