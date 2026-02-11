Enable()
{
  if (!Enabled())
  {
    state &= ENABLED;

    OnEnable();
  }
}
