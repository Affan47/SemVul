PyToken_ThreeChars(int c1, int c2, int c3)
{
    switch (c1) {
    case '<':
        switch (c2) {
        case '<':
            switch (c3) {
            case '=':
                return LEFTSHIFTEQUAL;
            }
            break;
        }
        break;
    case '>':
        switch (c2) {
        case '>':
            switch (c3) {
            case '=':
                return RIGHTSHIFTEQUAL;
            }
            break;
        }
        break;
    case '*':
        switch (c2) {
        case '*':
            switch (c3) {
            case '=':
                return DOUBLESTAREQUAL;
            }
            break;
        }
        break;
    case '/':
        switch (c2) {
        case '/':
            switch (c3) {
            case '=':
                return DOUBLESLASHEQUAL;
            }
            break;
        }
        break;
    }
    return OP;
}
