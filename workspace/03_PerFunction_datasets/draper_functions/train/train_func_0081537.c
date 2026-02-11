LoadReference(Reference* ref) {


  bool was_in_spilled_code = in_spilled_code_;
  in_spilled_code_ = false;

  Comment cmnt(masm_, "[ LoadReference");
  Expression* e = ref->expression();
  Property* property = e->AsProperty();
  Variable* var = e->AsVariableProxy()->AsVariable();

  if (property != NULL) {


    Load(property->obj());
    if (property->key()->IsPropertyName()) {
      ref->set_type(Reference::NAMED);
    } else {
      Load(property->key());
      ref->set_type(Reference::KEYED);
    }
  } else if (var != NULL) {


    if (var->is_global()) {


      frame_->Spill(rax);
      LoadGlobal();
      ref->set_type(Reference::NAMED);
    } else {
      ASSERT(var->AsSlot() != NULL);
      ref->set_type(Reference::SLOT);
    }
  } else {

    Load(e);
    frame_->CallRuntime(Runtime::kThrowReferenceError, 1);
  }

  in_spilled_code_ = was_in_spilled_code;
}
