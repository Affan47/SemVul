NewNode(P_WBXML_INFO buffer, WBXML_NODE_TYPE type)
{
	if (buffer)
	{
		P_WBXML_NODE newnode = malloc(sizeof(WBXML_NODE));

		if (newnode)
		{
			newnode->m_prev = NULL;
			newnode->m_child = NULL;

			if (buffer->m_curnode)
			{

				newnode->m_parent = buffer->m_curnode;
				newnode->m_next = buffer->m_curnode->m_child;

				if (buffer->m_curnode->m_child)
				{
					((P_WBXML_NODE)buffer->m_curnode->m_child)->m_prev = newnode;
				}

				buffer->m_curnode->m_child = newnode;
			}
			else
			{

				newnode->m_parent = NULL;
				newnode->m_next = buffer->m_tree;

				if (buffer->m_tree)
				{
					buffer->m_tree->m_prev = newnode;
				}

				buffer->m_tree = newnode;
			}

			newnode->m_page = buffer->m_curpage;
			newnode->m_type = type;
			newnode->m_data = NULL;
		}
		else
		{
			ParseError(ERR_NOT_ENOUGH_MEMORY);
		}

		return newnode;
	}
	else
	{
		ParseError(ERR_INTERNAL_BAD_PARAM);
	}

	return NULL;
}
