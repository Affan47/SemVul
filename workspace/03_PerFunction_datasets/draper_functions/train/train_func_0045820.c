handle_enter( void* fha, uint64_t time, uint32_t function,
               uint32_t process, uint32_t source, OTF_KeyValueList* kvlist ) {

    AllData* alldata= (AllData*) fha;


    list<StackType>& stack= alldata->stackPerProcess[ process ];
    stack.push_back( StackType( function, time ) );

    if(alldata->params.dispersion.mode == DISPERSION_MODE_PERCALLPATH)
    {


        std::ostringstream os;
        os << " " << function;
        callpath[process] += os.str();
    }

    return OTF_RETURN_OK;
}
