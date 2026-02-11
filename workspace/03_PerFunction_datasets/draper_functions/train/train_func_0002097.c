_inc_by_one(QString &str, int position)
{
    for (int i = position; i >= 0; i--) {
        char last_char = str[i].toLatin1();
        switch (last_char) {
        case '0':
            str[i] = '1';
            break;
        case '1':
            str[i] = '2';
            break;
        case '2':
            str[i] = '3';
            break;
        case '3':
            str[i] = '4';
            break;
        case '4':
            str[i] = '5';
            break;
        case '5':
            str[i] = '6';
            break;
        case '6':
            str[i] = '7';
            break;
        case '7':
            str[i] = '8';
            break;
        case '8':
            str[i] = '9';
            break;
        case '9':
            str[i] = '0';
            if (i == 0) str.prepend(QLatin1Char('1'));
            continue;
        case '.':
            continue;
        }
        break;
    }
}
