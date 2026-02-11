getPayloadLength() const
{
  if(!payload_) {
    return 0;
  }

  if(!auth_tag_) {
    return (length_ > sizeof(struct HeaderStruct)) ? (length_ - sizeof(struct HeaderStruct)) : 0;
  }

  return (length_ > (sizeof(struct HeaderStruct) + auth_tag_length_)) ? (length_ - sizeof(struct HeaderStruct) - auth_tag_length_) : 0;
}
