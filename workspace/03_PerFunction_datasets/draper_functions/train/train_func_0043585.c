setupContainer( QLanguageItem * container )
{
	container->setMimeId( mimeId() );
	container->setStorageMode(true);
	container->unlinkFile();
}
