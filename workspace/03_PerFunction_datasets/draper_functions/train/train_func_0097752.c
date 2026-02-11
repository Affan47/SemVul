append_data_payload(const string& str)
{
  length += str.size();
  if (!payload.empty()) {
    if (payload.back().type == PayloadElement::DATA) {
      payload.back().data.append(str);
      return;
    }
  }

  PayloadElement e;
  e.type = PayloadElement::DATA;
  e.data = str;
  payload.push_back(e);
}
