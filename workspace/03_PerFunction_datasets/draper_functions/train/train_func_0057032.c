OnEvent(const SEvent &event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			gui::IGUIEnvironment* env = Device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
				case gui::EGET_MENU_ITEM_SELECTED:
				{
					gui::IGUIContextMenu* menu = (gui::IGUIContextMenu*)event.GUIEvent.Caller;
					s32 id = menu->getItemCommandId(menu->getSelectedItem());

					switch(id)
					{
						case GUI_ID_OPEN_TEXTURE:
							env->addFileOpenDialog(L"Please select a texture file to open");
						break;
						case GUI_ID_QUIT:
							stopApp();
						break;
					}
				}
				break;

				case gui::EGET_FILE_SELECTED:
				{

					gui::IGUIFileOpenDialog* dialog =
						(gui::IGUIFileOpenDialog*)event.GUIEvent.Caller;
					loadTexture(io::path(dialog->getFileName()).c_str());
				}
				break;

				default:
				break;
			}
		}

		return false;
	}
