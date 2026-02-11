complete_from_args(const wcstring &str,
                                     const wcstring &args,
                                     const wcstring &desc,
                                     complete_flags_t flags)
{

    std::vector<completion_t> possible_comp;

    bool is_autosuggest = (this->type() == COMPLETE_AUTOSUGGEST);
    parser_t parser(is_autosuggest ? PARSER_TYPE_COMPLETIONS_ONLY : PARSER_TYPE_GENERAL, false);


    if (! is_autosuggest)
        proc_push_interactive(0);

    parser.eval_args(args.c_str(), possible_comp);

    if (! is_autosuggest)
        proc_pop_interactive();

    this->complete_strings(str, desc.c_str(), 0, possible_comp, flags);
}
