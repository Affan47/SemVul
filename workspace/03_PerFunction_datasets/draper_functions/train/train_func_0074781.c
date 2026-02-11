SetRandomTestMode(bool test) {
  if (!test) {
    GetGlobalRng().reset(new SecureRandomGenerator());
  } else {
    GetGlobalRng().reset(new TestRandomGenerator());
  }
}
