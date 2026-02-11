DrawLine(PCell B, int Line, int Col, ChColor color, int Width) {
    if (Line < (int)ErrList.size())
        if (Col < int(ErrList[Line]->text.size())) {
            char str[1024];
            size_t len;

            len = UnTabStr(str, sizeof(str),
                           ErrList[Line]->text.c_str(),
                           ErrList[Line]->text.size());

            if ((int)len > Col)
                MoveStr(B, 0, Width, str + Col, color, Width);
        }
}
