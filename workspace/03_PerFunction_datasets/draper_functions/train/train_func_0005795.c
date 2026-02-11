slot_entry_acivate()
{
#ifdef _DEBUG
    std::cout << "CompletionEntry::slot_entry_acivate\n";
#endif

    if( ! completion() ) m_sig_activate.emit();
}
