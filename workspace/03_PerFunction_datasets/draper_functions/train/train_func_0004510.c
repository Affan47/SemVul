ExportPublicKeyInfo(std::vector<uint8>* output) {

  std::vector<uint8> bit_string;
  if (!ExportPublicKey(&bit_string))
    return false;


  std::list<uint8> content;
  PrependBitString(&bit_string[0], static_cast<int>(bit_string.size()),
                   &content);


  for (size_t i = sizeof(kRsaAlgorithmIdentifier); i > 0; --i)
    content.push_front(kRsaAlgorithmIdentifier[i - 1]);


  PrependTypeHeaderAndLength(kSequenceTag, content.size(), &content);


  output->reserve(content.size());
  output->assign(content.begin(), content.end());

  return true;
}
