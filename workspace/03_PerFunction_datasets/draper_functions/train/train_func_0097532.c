findMacro(const QString &str, int *pos, QString *ret)
{
    forever {
        int openPos = str.indexOf(QLatin1String("%{"), *pos);
        if (openPos < 0)
            return 0;
        int varPos = openPos + 2;
        int closePos = str.indexOf(QLatin1Char('}'), varPos);
        if (closePos < 0)
            return 0;
        int varLen = closePos - varPos;
        if (resolveMacro(str.mid(varPos, varLen), ret)) {
            *pos = openPos;
            return varLen + 3;
        }


        *pos = varPos;
    }
}
