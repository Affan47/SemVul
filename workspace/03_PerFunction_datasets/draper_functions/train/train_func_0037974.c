DebugString(int depth, string *contents) const {
  string prefix(depth * 2, ' ');
  ++depth;
  contents->append(" {\n");

  FormatLineOptions(depth, options(), contents);


  set<const Descriptor*> groups;
  for (int i = 0; i < field_count(); i++) {
    if (field(i)->type() == FieldDescriptor::TYPE_GROUP) {
      groups.insert(field(i)->message_type());
    }
  }
  for (int i = 0; i < extension_count(); i++) {
    if (extension(i)->type() == FieldDescriptor::TYPE_GROUP) {
      groups.insert(extension(i)->message_type());
    }
  }

  for (int i = 0; i < nested_type_count(); i++) {
    if (groups.count(nested_type(i)) == 0) {
      strings::SubstituteAndAppend(contents, "$0  message $1",
                                   prefix, nested_type(i)->name());
      nested_type(i)->DebugString(depth, contents);
    }
  }
  for (int i = 0; i < enum_type_count(); i++) {
    enum_type(i)->DebugString(depth, contents);
  }
  for (int i = 0; i < field_count(); i++) {
    field(i)->DebugString(depth, contents);
  }

  for (int i = 0; i < extension_range_count(); i++) {
    strings::SubstituteAndAppend(contents, "$0  extensions $1 to $2;\n",
                                 prefix,
                                 extension_range(i)->start,
                                 extension_range(i)->end - 1);
  }


  const Descriptor* containing_type = NULL;
  for (int i = 0; i < extension_count(); i++) {
    if (extension(i)->containing_type() != containing_type) {
      if (i > 0) strings::SubstituteAndAppend(contents, "$0  }\n", prefix);
      containing_type = extension(i)->containing_type();
      strings::SubstituteAndAppend(contents, "$0  extend .$1 {\n",
                                   prefix, containing_type->full_name());
    }
    extension(i)->DebugString(depth + 1, contents);
  }
  if (extension_count() > 0)
    strings::SubstituteAndAppend(contents, "$0  }\n", prefix);

  strings::SubstituteAndAppend(contents, "$0}\n", prefix);
}
