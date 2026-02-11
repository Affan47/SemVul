Set(const char* a_c_string) {

  const char* const temp = MyString::CloneCString(a_c_string);
  delete[] c_string_;
  c_string_ = temp;
}
