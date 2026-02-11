create(const InitStateString &username,
                                                   const InitStateString &password)
    {

        boost::shared_ptr<AuthProvider> provider;
#if (defined USE_GSSO || defined USE_UOA)
        provider = createSignonAuthProvider(username, password);
#endif
        return provider;
    }
}
