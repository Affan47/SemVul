json_artifact_status_to_string( char isNew, char isDel ){
  return isNew
    ? "added"
    : (isDel
       ? "removed"
       : "modified");
}
