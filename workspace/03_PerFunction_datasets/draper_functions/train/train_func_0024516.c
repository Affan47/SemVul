VisitVariableProxy(VariableProxy* node) {
  Variable* var = node->AsVariable();
  if (var != NULL) {
    if (var->type()->IsKnown()) {
      node->type()->CopyFrom(var->type());
    } else if (node->type()->IsLikelySmi()) {
      var->type()->SetAsLikelySmi();
    }

    if (FLAG_safe_int32_compiler) {
      if (var->IsStackAllocated() &&
          !var->is_arguments() &&
          var->mode() != Variable::CONST) {
        node->set_side_effect_free(true);
      }
    }
  }
}
