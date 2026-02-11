addInstance(scene::ISceneNode* parent,
			scene::ISceneManager* mgr)
		{
			#ifdef COLLADA_READER_DEBUG
			os::Printer::log("COLLADA: Constructing scene instance", Id.c_str());
			#endif

			if (Childs.size()==0)
				return 0;

			scene::IDummyTransformationSceneNode* s = mgr->addDummyTransformationSceneNode(parent);
			if (s)
			{
				s->setName(getId());
				s->getRelativeTransformationMatrix() = Transformation;
				core::stringc t;
				for (u32 i=0; i<16; ++i)
				{
					t+=core::stringc(Transformation[i]);
					t+=" ";
				}
os::Printer::log("COLLADA: Transformation", t.c_str());

				for (u32 i=0; i<Childs.size(); ++i)
					Childs[i]->addInstance(s, mgr);
			}

			return s;
		}
