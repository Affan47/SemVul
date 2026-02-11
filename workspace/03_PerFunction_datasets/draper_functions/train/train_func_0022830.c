IsFlushable(SharedFunctionInfo* shared_info) {


    if (shared_info->unchecked_code()->IsMarked()) {
      shared_info->set_code_age(0);
      return false;
    }


    if (!(shared_info->is_compiled() && HasSourceCode(shared_info))) {
      return false;
    }


    Object* function_data = shared_info->function_data();
    if (function_data->IsHeapObject() &&
        (SafeMap(function_data)->instance_type() ==
         FUNCTION_TEMPLATE_INFO_TYPE)) {
      return false;
    }


    if (shared_info->code()->kind() != Code::FUNCTION) return false;


    if (!shared_info->allows_lazy_compilation()) return false;


    if (shared_info->is_toplevel()) return false;


    if (shared_info->code_age() < kCodeAgeThreshold) {
      shared_info->set_code_age(shared_info->code_age() + 1);
      return false;
    }

    return true;
  }
