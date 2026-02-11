GetMessage(int number,
                                            const Descriptor* message_type,
                                            MessageFactory* factory) const {
  map<int, Extension>::const_iterator iter = extensions_.find(number);
  if (iter == extensions_.end() || iter->second.is_cleared) {

    return *factory->GetPrototype(message_type);
  } else {
    GOOGLE_DCHECK_TYPE(iter->second, OPTIONAL, MESSAGE);
    return *iter->second.message_value;
  }
}
