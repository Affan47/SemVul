makeSubsetSeeds( SubsetSuffixArray indexes[],
			  const LastdbArguments& args, const Alphabet& alph ){
  unsigned numOfIndexes = 0;

  for( unsigned x = 0; x < args.subsetSeedFiles.size(); ++x ){
    CyclicSubsetSeed& seed = indexes[ numOfIndexes++ ].getSeed();
    seed.fromFile( args.subsetSeedFiles[x],
		   args.isCaseSensitive, alph.encode );
  }

  for( unsigned x = 0; x < args.seedPatterns.size(); ++x ){
    CyclicSubsetSeed& seed = indexes[ numOfIndexes++ ].getSeed();
    seed.fromCodeString( args.seedPatterns[x], alph.letters,
			 args.isCaseSensitive, alph.encode );
  }

  if( numOfIndexes == 0 ){
    CyclicSubsetSeed& seed = indexes[ numOfIndexes++ ].getSeed();
    if( alph.letters == alph.dna ){
      seed.fromString( seed.yassSeed, args.isCaseSensitive, alph.encode );
    }
    else if( alph.letters == alph.protein ){
      seed.fromString( seed.proteinSeed, args.isCaseSensitive, alph.encode );
    }
    else{
      seed.fromCodeString( "1", alph.letters,
			   args.isCaseSensitive, alph.encode );
    }
  }

  return numOfIndexes;
}
