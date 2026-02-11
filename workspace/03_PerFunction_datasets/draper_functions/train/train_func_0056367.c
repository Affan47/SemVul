IsMatch(Object* string) {


    if (hash_ != HashForObject(string)) {
      return false;
    }
    return string_->Equals(String::cast(string));
  }
