padL(int len, char c) {
 if (length()>=len) return *this;
 make_unique();
 Data *data = new_data(len);
 ::memcpy(data->chars, chars(), length());
 ::memset(&data->chars[length()],c,len-length());
 replace_data(data);
 return *this;
 }
