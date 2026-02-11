expand (class LtlGraphNode& node,
		  std::stack<class LtlGraphNode*>& to_expand) const
{
  if (m_con) {
    if (!node.m_old[m_left.m_num])
      node.m_new.assign_true (m_left.m_num);
    if (!node.m_old[m_right.m_num])
      node.m_new.assign_true (m_right.m_num);
  }
  else {
    class BitVector new_set (node.m_new);
    if (!node.m_old[m_left.m_num])
      new_set.assign_true (m_left.m_num);
    if (!node.m_old[m_right.m_num])
      node.m_new.assign_true (m_right.m_num);
    to_expand.push (new class LtlGraphNode (node.m_incoming, new_set,
					    node.m_old, node.m_atomic,
					    node.m_next));
  }
}
