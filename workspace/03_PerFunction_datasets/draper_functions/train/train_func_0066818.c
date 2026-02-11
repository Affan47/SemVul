getLinearization()
{
  if (!linearization) {
    linearization = new Linearization(str);
  }
  return linearization;
}
