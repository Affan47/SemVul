press()
{
    if (hasState()) fakeDevice()->setProperty("stateValue", !stateValue());
    emit pressed(type(), fakeDevice()->udi());
}
