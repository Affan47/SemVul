_insertFixup(Node* x)
{
	Node* y;
	UT_ASSERT(x);

	Iterator it(this, x);
	fixSize(it);

	while ((x != m_pRoot) && (x->parent->color == Node::red))
	{
		if (x->parent == x->parent->parent->left)
		{

			y = x->parent->parent->right;
		    if (y && y->color == Node::red)
			{


				x->parent->color = Node::black;
				y->color = Node::black;
				x->parent->parent->color = Node::red;

				x = x->parent->parent;
			}
			else
			{

				if (x == x->parent->right)
				{


					x = x->parent;
					_leftRotate(x);
				}

				x->parent->color = Node::black;
				x->parent->parent->color = Node::red;
				_rightRotate(x->parent->parent);
			}
		}
		else
		{

			y = x->parent->parent->left;
			if (y && y->color == Node::red)
			{

				x->parent->color = Node::black;
				y->color = Node::black;
				x->parent->parent->color = Node::red;

				x = x->parent->parent;
			}
			else
			{

				if (x == x->parent->left)
				{


					x = x->parent;
					_rightRotate(x);
				}

				x->parent->color = Node::black;
				x->parent->parent->color = Node::red;
				_leftRotate(x->parent->parent);
			}
		}
	}


	m_pRoot->color = Node::black;
}
