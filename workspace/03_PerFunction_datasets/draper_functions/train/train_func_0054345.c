resOpenFrac(int id1In, int id2In, int id3In) {


  double answer = 1.;


  if (isParticle(id1In)) answer  = pdt[abs(id1In)].resOpenFrac(id1In);


  if (isParticle(id2In)) answer *= pdt[abs(id2In)].resOpenFrac(id2In);


  if (isParticle(id3In)) answer *= pdt[abs(id2In)].resOpenFrac(id3In);


  return answer;

}
