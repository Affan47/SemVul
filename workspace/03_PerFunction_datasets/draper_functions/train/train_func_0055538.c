PrintHeader(MallocExtensionWriter* writer,
                 const char* label, void** entries) {

  uintptr_t total_count = 0;
  uintptr_t total_size = 0;
  for (void** entry = entries; Count(entry) != 0; entry += 3 + Depth(entry)) {
    total_count += Count(entry);
    total_size += Size(entry);
  }

  const char* const kTitle = "heap profile: ";
  writer->append(kTitle, strlen(kTitle));
  PrintCountAndSize(writer, total_count, total_size);
  writer->append(" ", 1);
  writer->append(label, strlen(label));
  writer->append("\n", 1);
}
