ParseMessageStatement(DescriptorProto* message,
                                   const LocationRecorder& message_location) {
  if (TryConsume(";")) {

    return true;
  } else if (LookingAt("message")) {
    LocationRecorder location(message_location,
                              DescriptorProto::kNestedTypeFieldNumber,
                              message->nested_type_size());
    return ParseMessageDefinition(message->add_nested_type(), location);
  } else if (LookingAt("enum")) {
    LocationRecorder location(message_location,
                              DescriptorProto::kEnumTypeFieldNumber,
                              message->enum_type_size());
    return ParseEnumDefinition(message->add_enum_type(), location);
  } else if (LookingAt("extensions")) {
    LocationRecorder location(message_location,
                              DescriptorProto::kExtensionRangeFieldNumber);
    return ParseExtensions(message, location);
  } else if (LookingAt("extend")) {
    LocationRecorder location(message_location,
                              DescriptorProto::kExtensionFieldNumber);
    return ParseExtend(message->mutable_extension(),
                       message->mutable_nested_type(),
                       message_location,
                       DescriptorProto::kNestedTypeFieldNumber,
                       location);
  } else if (LookingAt("option")) {
    LocationRecorder location(message_location,
                              DescriptorProto::kOptionsFieldNumber);
    return ParseOption(message->mutable_options(), location);
  } else {
    LocationRecorder location(message_location,
                              DescriptorProto::kFieldFieldNumber,
                              message->field_size());
    return ParseMessageField(message->add_field(),
                             message->mutable_nested_type(),
                             message_location,
                             DescriptorProto::kNestedTypeFieldNumber,
                             location);
  }
}
