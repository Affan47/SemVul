run() {
        static const QChar tilde = '~';


        assert(m_prepend.isEmpty());
        struct passwd* pw;
        while ((pw = ::getpwent()) && !terminationRequested())
            addMatch(tilde + QString::fromLocal8Bit(pw->pw_name));

        ::endpwent();

        addMatch(QString(tilde));

        done();
    }
}
