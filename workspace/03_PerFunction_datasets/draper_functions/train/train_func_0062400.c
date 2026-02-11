SetProperties(Handle<String> name, int start_position, int end_position,
                     Handle<SharedFunctionInfo> info) {
    HandleScope scope;
    this->SetField(kFunctionNameOffset_, name);
    Handle<JSValue> info_holder = WrapInJSValue(*info);
    this->SetField(kSharedInfoOffset_, info_holder);
    this->SetSmiValueField(kStartPositionOffset_, start_position);
    this->SetSmiValueField(kEndPositionOffset_, end_position);
  }
