GetPrototype(const Descriptor* type) {
  const DynamicMessage::TypeInfo** target = &prototypes_->map_[type];
  if (*target != NULL) {

    return (*target)->prototype.get();
  }

  DynamicMessage::TypeInfo* type_info = new DynamicMessage::TypeInfo;
  *target = type_info;

  type_info->type = type;
  type_info->pool = (pool_ == NULL) ? type->file()->pool() : pool_;
  type_info->factory = this;


  int* offsets = new int[type->field_count()];
  type_info->offsets.reset(offsets);


  int size = sizeof(DynamicMessage);
  size = AlignOffset(size);


  type_info->has_bits_offset = size;
  int has_bits_array_size =
    DivideRoundingUp(type->field_count(), bitsizeof(uint32));
  size += has_bits_array_size * sizeof(uint32);
  size = AlignOffset(size);


  if (type->extension_range_count() > 0) {
    type_info->extensions_offset = size;
    size += sizeof(ExtensionSet);
    size = AlignOffset(size);
  } else {

    type_info->extensions_offset = -1;
  }


  for (int i = 0; i < type->field_count(); i++) {

    int field_size = FieldSpaceUsed(type->field(i));
    size = AlignTo(size, min(kSafeAlignment, field_size));
    offsets[i] = size;
    size += field_size;
  }


  size = AlignOffset(size);
  type_info->unknown_fields_offset = size;
  size += sizeof(UnknownFieldSet);


  size = AlignOffset(size);
  type_info->size = size;


  void* base = operator new(size);
  memset(base, 0, size);
  DynamicMessage* prototype = new(base) DynamicMessage(type_info);
  type_info->prototype.reset(prototype);


  type_info->reflection.reset(
    new GeneratedMessageReflection(
      type_info->type,
      type_info->prototype.get(),
      type_info->offsets.get(),
      type_info->has_bits_offset,
      type_info->unknown_fields_offset,
      type_info->extensions_offset,
      type_info->pool,
      this,
      type_info->size));


  prototype->CrossLinkPrototypes();

  return prototype;
}
