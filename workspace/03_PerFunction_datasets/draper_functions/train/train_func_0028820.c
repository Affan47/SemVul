check_synchronization()
{
  if (attr & m_concurrent) {
    for (callee_desc* callee = callees; callee != NULL;
         callee = callee->next)
      {
        if (!(callee->method->attr & (m_serialized|m_synchronized)) &&
            !(callee->method->cls->attr & class_desc::cl_system) &&
            !(callee->attr & (callee_desc::i_self
                              |callee_desc::i_synchronized)) &&
            (strstr(callee->method->name.as_asciz(), "init>") == NULL) )
          {
            callee->message(msg_concurrent_call, callee->method);
          }
      }

    for (access_desc* accessor = accessors; accessor != NULL;
         accessor = accessor->next)
      {
        if (!(accessor->field->attr
              & (field_desc::f_volatile|field_desc::f_final
                 |field_desc::f_serialized))
            && !(accessor->field->cls->attr & class_desc::cl_system)
            && !(accessor->attr&(access_desc::a_new|access_desc::a_self)))
          {
            accessor->message(msg_concurrent_access,
                              &accessor->field->name,accessor->field->cls);
          }
      }
  }
}
