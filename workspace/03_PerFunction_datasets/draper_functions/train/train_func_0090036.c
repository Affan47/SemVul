FieldButton(FieldEditor* editor, FieldEditorAction* action) {
    editor_ = editor;
    action_ = action;
    Resource::ref(action_);
}
