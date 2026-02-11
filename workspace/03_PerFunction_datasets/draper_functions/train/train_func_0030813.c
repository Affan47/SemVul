operator()(WorldPacket& data, int32 loc_idx)
            {
                char const* text = NULL;
                if ((int32)i_textData->Content.size() > loc_idx + 1 && !i_textData->Content[loc_idx + 1].empty())
                    { text = i_textData->Content[loc_idx + 1].c_str(); }
                else
                    { text = i_textData->Content[0].c_str(); }

                ChatHandler::BuildChatPacket(data, i_msgtype, text, i_language, CHAT_TAG_NONE, i_object.GetObjectGuid(), i_object.GetNameForLocaleIdx(loc_idx),
                    i_target ? i_target->GetObjectGuid() : ObjectGuid(), i_target ? i_target->GetNameForLocaleIdx(loc_idx) : "");
            }
