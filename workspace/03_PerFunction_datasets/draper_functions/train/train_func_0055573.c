Insert (const char* s, int index) {
    display->Draw(output, canvas);
    register Perspective* p = perspective;

    char* copy = new char[strlen(s)+1];
    strcpy(copy, s);
    BufInsert(copy, index, strbuf, strbufsize, strcount);

    if (output != nil) {
	p->width = Math::max(p->width, output->GetFont()->Width(s));
    }
    p->height += lineheight;
    p->cury += lineheight;
    p->Update();

    if (index < strcount-1) {
        display->InsertLinesAfter(index-1, 1);
    }
    display->ReplaceText(index, s, strlen(s));
}
