chatbox_chat_init()
{
	int idx;

   chatbox_clear();


	for(idx=0;idx<MAX_BRIEF_CHAT_LINES;idx++){
      Brief_chat_next_index[idx] = idx+1;
	}
	Brief_chat_next_index[MAX_BRIEF_CHAT_LINES-1]=0;

	for(idx=MAX_BRIEF_CHAT_LINES-1; idx > 0 ; idx--){
		Brief_chat_prev_index[idx] = idx - 1;
	}
	Brief_chat_prev_index[0] = MAX_BRIEF_CHAT_LINES-1;


	Chatbox_recall_count = 0;
	Chatbox_recall_index = 0;
	Chatbox_recall_last = -1;
	memset(Chatbox_recall_lines,0,CHATBOX_MAX_RECALL_LINES * (CHATBOX_MAX_LEN + 2));
}
