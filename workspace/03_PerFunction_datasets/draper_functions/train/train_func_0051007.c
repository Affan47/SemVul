build_call_graph()
{
  if (attr & m_synchronized) {
    for (callee_desc* callee=callees; callee != NULL; callee=callee->next){
      callee->method->build_call_graph(this, callee, callee->attr);
    }
  }
}
