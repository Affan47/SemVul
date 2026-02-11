FullIsString() const {
  if (IsDeadCheck("v8::Value::IsString()")) return false;
  bool result = Utils::OpenHandle(this)->IsString();
  ASSERT_EQ(result, QuickIsString());
  return result;
}
