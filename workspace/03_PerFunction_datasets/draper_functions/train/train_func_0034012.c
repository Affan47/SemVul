GbgofficeExam(TranslatorManager *manager)
{
	trm = manager;


	set_default_size(400, 300);
	set_has_separator(false);


	vbox = get_vbox();
	vbox->pack_start(hbox1, false, false, 3);
	vbox->pack_start(hbox2, false, false, 3);
	vbox->pack_start(hbox3, true, true, 3);
	vbox->pack_start(hbox4, false, false, 3);


	button_new = add_button(Gtk::Stock::NEW, Gtk::RESPONSE_NONE);
	button_help = add_button(Gtk::Stock::HELP, Gtk::RESPONSE_NONE);
	button_close = add_button(Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE);


	question.set_markup(LT_(GUI_EXAM_TESTNOTSTARTED));


	tbuf = Gtk::TextBuffer::create();
	tbuf->set_text(LT_(GUI_EXAM_NEWTEST));
	ta.set_buffer(tbuf);
	ta.set_editable(false);
	ta.set_wrap_mode(Gtk::WRAP_WORD);
	ta.set_indent(4);
	ta_win.add(ta);
	ta_win.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);


	hbox1.pack_start(question, false, false, 5);
	hbox2.pack_start(answer, false, false, 5);
	hbox2.pack_end(emotion, false, false, 5);
	hbox2.pack_end(result, false, false, 5);
	hbox3.pack_start(ta_win, true, true, 5);
	hbox4.pack_end(pbar, true, true, 5);


	button_help->signal_clicked().connect(sigc::mem_fun(*this, &GbgofficeExam::on_help_button));
	button_new->signal_clicked().connect(sigc::mem_fun(*this, &GbgofficeExam::on_new_button));
	answer.signal_activate().connect(sigc::mem_fun(*this, &GbgofficeExam::answer_given));

	reset();
	dict = trm->getTestDictionaryObject(0, 0);
	dict->separateMeanings = true;
	dict->boldDecoration = false;
	dict->htmlOutput = false;


	show_all_children();
	run();
}
