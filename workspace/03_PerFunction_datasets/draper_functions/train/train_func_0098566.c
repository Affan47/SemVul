posix_thread_function(void*c)
{
thread_traits<posix> ::_Ctype*ct=
(thread_traits<posix> ::_Ctype*)c;
try{
ct->operator()();
}catch(...){
ct->exit();
}
return NULL;
}
