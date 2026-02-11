replaceImg3Signature(AbstractFile* file, AbstractFile* signature) {
  Img3Info* info = (Img3Info*) file->data;
  size_t signature_size = signature->getLength(signature);
  Img3Element* element = (Img3Element*) readImg3Element(signature);

  int i = 0;
  Img3Element* previous = element;
  for (i = previous->header->size; i < signature_size; i += previous->header->size) {
    previous->next = (Img3Element*) readImg3Element(signature);
    previous = previous->next;
  }

  Img3Element* current = info->data;
  while (current->next != info->shsh) {
    current = current->next;
  }

  signature->seek(signature, 0);
  current->next = element;
  info->dirty = TRUE;
}
