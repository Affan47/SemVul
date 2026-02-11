visit(While* node)
{
	Node* cond = node->getCondition();
	size_t start_while = m_builder->getSize();

	cond->accept(*this);

	IR& jmpz = m_builder->push(OP_JMPZ, createOp(cond));

	m_cont.push(AddrVector());
	m_brks.push(AddrVector());
	m_brks.top().push_back(start_while);

	node->getBlock()->accept(*this);

	if (!m_brks.top().empty()) {

		for (size_t i = 0, j = m_brks.top().size(); i < j; ++i) {
			m_builder->getAt(m_brks.top()[i]).op1.jmp_addr = m_builder->getSize() + 1;
		}
	}

	m_cont.pop();
	m_brks.pop();

	m_builder->push(OP_JMP, Operand(JMP_ADDR, start_while));

	jmpz.op2 = Operand(JMP_ADDR, m_builder->getSize());
}
