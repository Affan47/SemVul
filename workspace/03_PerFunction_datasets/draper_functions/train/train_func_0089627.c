findItem(const char *name, int32_t length) const {
    int32_t i, start, limit;
    int result;


    start=0;
    limit=itemCount;
    while(start<limit) {
        i=(start+limit)/2;
        if(length>=0) {
            result=strncmp(name, items[i].name, length);
        } else {
            result=strcmp(name, items[i].name);
        }

        if(result==0) {

            if(length>=0) {


                while(i>0 && 0==strncmp(name, items[i-1].name, length)) {
                    --i;
                }
            }
            return i;
        } else if(result<0) {
            limit=i;
        } else  {
            start=i+1;
        }
    }

    return ~start;
}
