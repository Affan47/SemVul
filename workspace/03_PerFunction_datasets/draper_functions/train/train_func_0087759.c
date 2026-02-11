writeArrayValue(const Value &value) {
  unsigned size = value.size();
  if (size == 0)
    pushValue("[]");
  else {
    bool isArrayMultiLine = isMultineArray(value);
    if (isArrayMultiLine) {
      writeWithIndent("[");
      indent();
      bool hasChildValue = !childValues_.empty();
      unsigned index = 0;
      for (;;) {
        const Value &childValue = value[index];
        writeCommentBeforeValue(childValue);
        if (hasChildValue)
          writeWithIndent(childValues_[index]);
        else {
          writeIndent();
          writeValue(childValue);
        }
        if (++index == size) {
          writeCommentAfterValueOnSameLine(childValue);
          break;
        }
        document_ += ",";
        writeCommentAfterValueOnSameLine(childValue);
      }
      unindent();
      writeWithIndent("]");
    } else
    {
      assert(childValues_.size() == size);
      document_ += "[ ";
      for (unsigned index = 0; index < size; ++index) {
        if (index > 0)
          document_ += ", ";
        document_ += childValues_[index];
      }
      document_ += " ]";
    }
  }
}
