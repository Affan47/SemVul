strescape(pool_t p, char *buf, int len)
{
    int i,j,newlen = len;
    char *temp;

    if (buf == NULL || len < 0) return NULL;

    for(i=0;i<len;i++)
    {
        switch(buf[i])
        {
        case '&':
            newlen+=5;
            break;
        case '\'':
            newlen+=6;
            break;
        case '\"':
            newlen+=6;
            break;
        case '<':
            newlen+=4;
            break;
        case '>':
            newlen+=4;
            break;
        }
    }

    if(p != NULL)
        temp = pmalloc(p,newlen+1);
    else
        temp = malloc(newlen+1);
    if(newlen == len)
    {
        memcpy(temp,buf,len);
        temp[len] = '\0';
        return temp;
    }

    for(i=j=0;i<len;i++)
    {
        switch(buf[i])
        {
        case '&':
            memcpy(&temp[j],"&amp;",5);
            j += 5;
            break;
        case '\'':
            memcpy(&temp[j],"&apos;",6);
            j += 6;
            break;
        case '\"':
            memcpy(&temp[j],"&quot;",6);
            j += 6;
            break;
        case '<':
            memcpy(&temp[j],"&lt;",4);
            j += 4;
            break;
        case '>':
            memcpy(&temp[j],"&gt;",4);
            j += 4;
            break;
        default:
            temp[j++] = buf[i];
        }
    }
    temp[j] = '\0';
    return temp;
}
