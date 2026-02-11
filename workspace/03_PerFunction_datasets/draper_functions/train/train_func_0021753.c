ExpandOnce(
    ExpandEmitter *output_buffer,
    const TemplateDictionaryInterface &dictionary,
    const char* const filename,
    PerExpandData *per_expand_data,
    const TemplateCache *cache) const {
  bool error_free = true;


  TemplateCache* cache_ptr = const_cast<TemplateCache*>(cache);


  if (per_expand_data->annotate()) {
    per_expand_data->annotator()->EmitOpenInclude(output_buffer,
                                                  token_.ToString());
  }


  if (AnyMightModify(token_.modvals, per_expand_data)) {
    string sub_template;
    StringEmitter subtemplate_buffer(&sub_template);
    if (!cache_ptr->ExpandLocked(filename, strip_,
                                 &subtemplate_buffer,
                                 &dictionary,
                                 per_expand_data)) {
      EmitMissingInclude(filename, output_buffer, per_expand_data);
      error_free = false;
    } else {
      EmitModifiedString(token_.modvals,
                         sub_template.data(), sub_template.size(),
                         per_expand_data, output_buffer);
    }
  } else {

    if (!cache_ptr->ExpandLocked(filename, strip_,
                                 output_buffer,
                                 &dictionary,
                                 per_expand_data)) {
      EmitMissingInclude(filename, output_buffer, per_expand_data);
      error_free = false;
    }
  }
  if (per_expand_data->annotate()) {
    per_expand_data->annotator()->EmitCloseInclude(output_buffer);
  }
  return error_free;
}
