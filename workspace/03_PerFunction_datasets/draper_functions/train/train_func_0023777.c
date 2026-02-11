WriteLogOpening(const std::string& file)
{
	Logger* l = DefaultLogger::get();
	if (!l) {
		return;
	}
	l->info("Load " + file);


	const unsigned int flags = aiGetCompileFlags();
	l->debug(format()
		<< "Assimp "
		<< aiGetVersionMajor()
		<< "."
		<< aiGetVersionMinor()
		<< "."
		<< aiGetVersionRevision()

		<< " "
#if defined(ASSIMP_BUILD_ARCHITECTURE)
		<< ASSIMP_BUILD_ARCHITECTURE
#elif defined(_M_IX86) || defined(__x86_32__) || defined(__i386__)
		<< "x86"
#elif defined(_M_X64) || defined(__x86_64__)
		<< "amd64"
#elif defined(_M_IA64) || defined(__ia64__)
		<< "itanium"
#elif defined(__ppc__) || defined(__powerpc__)
		<< "ppc32"
#elif defined(__powerpc64__)
		<< "ppc64"
#elif defined(__arm__)
		<< "arm"
#else
	<< "<unknown architecture>"
#endif

		<< " "
#if defined(ASSIMP_BUILD_COMPILER)
		<< ASSIMP_BUILD_COMPILER
#elif defined(_MSC_VER)
		<< "msvc"
#elif defined(__GNUC__)
		<< "gcc"
#else
		<< "<unknown compiler>"
#endif

#ifdef ASSIMP_BUILD_DEBUG
		<< " debug"
#endif

		<< (flags & ASSIMP_CFLAGS_NOBOOST ? " noboost" : "")
		<< (flags & ASSIMP_CFLAGS_SHARED  ? " shared" : "")
		<< (flags & ASSIMP_CFLAGS_SINGLETHREADED  ? " singlethreaded" : "")
		);
}
