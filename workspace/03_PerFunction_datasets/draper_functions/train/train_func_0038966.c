jv_setpath(jv root, jv path, jv value) {
  if (jv_get_kind(path) != JV_KIND_ARRAY) {
    jv_free(value);
    jv_free(root);
    jv_free(path);
    return jv_invalid_with_msg(jv_string("Path must be specified as an array"));
  }
  if (!jv_is_valid(root)){
    jv_free(value);
    jv_free(path);
    return root;
  }
  if (jv_array_length(jv_copy(path)) == 0) {
    jv_free(path);
    jv_free(root);
    return value;
  }
  jv pathcurr = jv_array_get(jv_copy(path), 0);
  jv pathrest = jv_array_slice(path, 1, jv_array_length(jv_copy(path)));
  return jv_set(root, pathcurr,
                jv_setpath(jv_get(jv_copy(root), jv_copy(pathcurr)), pathrest, value));
}
