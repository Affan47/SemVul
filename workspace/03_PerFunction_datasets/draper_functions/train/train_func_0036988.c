PWhiteSpace(WhiteSpaceControl,EOFControl)

int WhiteSpaceControl,EOFControl;
{
    int Returned = PSUCCEEDED;

    if (WhiteSpaceControl == PSTRIPWHITESPACE1) {
        while((PChar = getc(PCIFFileDesc)) == ' ' Or PChar == '\t' Or
            PChar == '\n' Or PChar == ',') {
            if (PChar == EOF) {
                if (EOFControl != PDONTFAILONEOF) {
                    PErrorEOF();
                    Returned = PFAILED;
                }
                break;
            }
         }
         ungetc((char)PChar,PCIFFileDesc);
    }
    elif (WhiteSpaceControl == PSTRIPWHITESPACE2) {
        while((PChar = getc(PCIFFileDesc)) != '-' And PChar != '('
            And PChar != ')' And (PChar < 'A' Or PChar > 'Z')
                And (PChar < '0' Or PChar > '9') And PChar != ';') {
            if (PChar == EOF) {
                if (EOFControl != PDONTFAILONEOF) {
                    PErrorEOF();
                    Returned = PFAILED;
                }
                break;
            }
        }
        ungetc((char)PChar,PCIFFileDesc);
    }
    elif (WhiteSpaceControl == PSTRIPWHITESPACE3) {
        while((PChar = getc(PCIFFileDesc)) != '-' And PChar != '('
            And PChar != ')' And (PChar< '0' Or PChar > '9') And
                PChar != ';') {
            if (PChar == EOF) {
                if (EOFControl != PDONTFAILONEOF) {
                    PErrorEOF();
                    Returned = PFAILED;
                }
                break;
            }
        }
        ungetc((char)PChar,PCIFFileDesc);
    }
    return (Returned);
}
