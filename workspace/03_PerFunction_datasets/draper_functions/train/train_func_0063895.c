ParseExtensions(DescriptorProto* message,
                             const LocationRecorder& extensions_location) {

  DO(Consume("extensions"));

  do {

    LocationRecorder location(extensions_location,
                              message->extension_range_size());

    DescriptorProto::ExtensionRange* range = message->add_extension_range();
    location.RecordLegacyLocation(
        range, DescriptorPool::ErrorCollector::NUMBER);

    int start, end;
    io::Tokenizer::Token start_token;

    {
      LocationRecorder start_location(
          location, DescriptorProto::ExtensionRange::kStartFieldNumber);
      start_token = input_->current();
      DO(ConsumeInteger(&start, "Expected field number range."));
    }

    if (TryConsume("to")) {
      LocationRecorder end_location(
          location, DescriptorProto::ExtensionRange::kEndFieldNumber);
      if (TryConsume("max")) {
        end = FieldDescriptor::kMaxNumber;
      } else {
        DO(ConsumeInteger(&end, "Expected integer."));
      }
    } else {
      LocationRecorder end_location(
          location, DescriptorProto::ExtensionRange::kEndFieldNumber);
      end_location.StartAt(start_token);
      end_location.EndAt(start_token);
      end = start;
    }


    ++end;

    range->set_start(start);
    range->set_end(end);
  } while (TryConsume(","));

  DO(Consume(";"));
  return true;
}
